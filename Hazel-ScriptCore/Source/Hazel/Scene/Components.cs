﻿using System;
using Hazel;

namespace Hazel
{
    public abstract class Component
    {
        public Entity Entity { get; internal set;}
    }

    public class TransformComponent : Component
    {
        public Vector3 Translation
        { get
            {
                InternalCalls.TransformComponent_GetTranslation(Entity.ID, out Vector3 translation);
                return translation;
            }
            set
            {
                InternalCalls.TransformComponent_SetTranslation(Entity.ID, ref value);
            }
        }
    }

    public class Rigidbody2DComponent : Component
    {
        public void ApplyLinearImpulse(Vector2 impulse, Vector2 point, bool wake = true)
        {
            InternalCalls.Rigidbody2DComponent_ApplyLinearImpulse(Entity.ID, ref impulse, ref point, ref wake);
        }
    }
}


