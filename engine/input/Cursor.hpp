// Ouzel by Elviss Strazdins

#ifndef OUZEL_INPUT_CURSOR_HPP
#define OUZEL_INPUT_CURSOR_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "InputSystem.hpp"
#include "SystemCursor.hpp"
#include "../graphics/PixelFormat.hpp"
#include "../math/Size.hpp"
#include "../math/Vector.hpp"

namespace ouzel::input
{
    class Cursor final
    {
    public:
        explicit Cursor(InputManager& initInputManager);
        Cursor(InputManager& initInputManager, SystemCursor systemCursor);
        Cursor(InputManager& initInputManager, const std::string& filename, const Vector<float, 2>& hotSpot = Vector<float, 2>{});
        ~Cursor();

        Cursor(const Cursor&) = delete;
        Cursor& operator=(const Cursor&) = delete;

        Cursor(Cursor&&) = delete;
        Cursor& operator=(Cursor&&) = delete;

        void init(SystemCursor systemCursor);
        void init(const std::string& filename, const Vector<float, 2>& hotSpot = Vector<float, 2>{});
        void init(const std::vector<std::uint8_t>& data,
                  const Size<float, 2>& size,
                  graphics::PixelFormat pixelFormat,
                  const Vector<float, 2>& hotSpot);

        auto getCursorResource() const noexcept { return cursorResource; }

    private:
        InputManager& inputManager;
        std::size_t cursorResource = 0;
    };
}

#endif // OUZEL_INPUT_CURSOR_HPP
