// Ouzel by Elviss Strazdins

#include "Component.hpp"
#include "Actor.hpp"
#include "../math/MathUtils.hpp"

namespace ouzel::scene
{
    Component::~Component()
    {
        if (actor) actor->removeComponent(*this);
    }

    void Component::draw(const Matrix<float, 4>&,
                         float,
                         const Matrix<float, 4>&,
                         bool)
    {
    }

    bool Component::pointOn(const Vector<float, 2>& position) const
    {
        return boundingBox.containsPoint(Vector<float, 3>{position});
    }

    namespace
    {
        template <class Iterator>
        void gatherPolygonProjectionExtents(Iterator begin, Iterator end,
                                            const Vector<float, 2>& v,
                                            float& outMin, float& outMax) noexcept
        {
            auto i = begin;
            if (i != end)
            {
                outMin = outMax = v.dot(*i);
                ++i;

                for (; i != end; ++i)
                {
                    const float d = v.dot(*i);
                    if (d < outMin) outMin = d;
                    else if (d > outMax) outMax = d;
                }
            }
        }

        template <class IteratorA, class IteratorB>
        bool findSeparatingAxis(IteratorA aBegin, IteratorA aEnd,
                                IteratorB bBegin, IteratorB bEnd) noexcept
        {
            Vector<float, 2> v;
            auto prev = aEnd - 1;
            for (auto cur = aBegin; cur != aEnd; ++cur)
            {
                const Vector<float, 2> edge = *cur - *prev;
                v.v[0] = edge.v[1];
                v.v[1] = -edge.v[0];

                float aMin = 0.0F;
                float aMax = 0.0F;
                float bMin = 0.0F;
                float bMax = 0.0F;
                gatherPolygonProjectionExtents(aBegin, aEnd, v, aMin, aMax);
                gatherPolygonProjectionExtents(bBegin, bEnd, v, bMin, bMax);

                if (aMax < bMin) return true;
                if (bMax < aMin) return true;

                prev = cur;
            }

            return false;
        }
    }

    bool Component::shapeOverlaps(const std::vector<Vector<float, 2>>& edges) const
    {
        const std::array<Vector<float, 2>, 4> boundingBoxEdges = {
            Vector<float, 2>{boundingBox.min},
            Vector<float, 2>{boundingBox.max.v[0], boundingBox.min.v[1]},
            Vector<float, 2>{boundingBox.max},
            Vector<float, 2>{boundingBox.min.v[0], boundingBox.max.v[1]}
        };

        if (findSeparatingAxis(boundingBoxEdges.begin(), boundingBoxEdges.end(),
                               edges.begin(), edges.end()))
            return false;

        if (findSeparatingAxis(edges.begin(), edges.end(),
                               boundingBoxEdges.begin(), boundingBoxEdges.end()))
            return false;

        return true;
    }

    void Component::removeFromActor()
    {
        if (actor) actor->removeComponent(*this);
    }

    void Component::setActor(Actor* newActor)
    {
        actor = newActor;
    }

    void Component::setLayer(Layer* newLayer)
    {
        layer = newLayer;
    }

    void Component::updateTransform()
    {
    }
}
