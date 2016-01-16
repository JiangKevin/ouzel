// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "Gamepad.h"

#ifdef __OBJC__
@class GCController;
typedef GCController* GCControllerPtr;
#else
#include <objc/objc.h>
typedef id GCControllerPtr;
#endif

namespace ouzel
{
    class InputApple;
    
    class GamepadApple: public Gamepad
    {
        friend InputApple;
    public:
        virtual bool isAttached() const override;
        virtual void setAbsoluteDpadValues(bool absoluteDpadValues) override;
        virtual bool isAbsoluteDpadValues() const override;
        
        virtual int32_t getPlayerIndex() const override;
        virtual bool setPlayerIndex(int32_t playerIndex) override;
        
        GCController* getController() const { return _controller; }
        
    protected:
        GamepadApple(GCControllerPtr controller);
        
        GCControllerPtr _controller;
    };
}
