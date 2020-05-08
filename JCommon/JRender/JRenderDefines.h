#ifndef JRENDERDEFINES
#define JRENDERDEFINES

enum JShaderType
{
	Shader_DefaultSprite = 0
};

namespace J
{
	namespace RENDER
	{
		/// A 2D column vector.
		struct JVec2
		{
			/// Default constructor does nothing (for performance).
			JVec2() {}

			/// Construct using coordinates.
			JVec2(float xIn, float yIn) : x(xIn), y(yIn) {}

			/// Set this vector to all zeros.
			void SetZero() { x = 0.0f; y = 0.0f; }

			/// Set this vector to some specified coordinates.
			void Set(float x_, float y_) { x = x_; y = y_; }

			/// Negate this vector.
			JVec2 operator -() const { JVec2 v; v.Set(-x, -y); return v; }

			/// Read from and indexed element.
			float operator () (int i) const
			{
				return (&x)[i];
			}

			/// Write to an indexed element.
			float& operator () (int i)
			{
				return (&x)[i];
			}

			/// Add a vector to this vector.
			void operator += (const JVec2& v)
			{
				x += v.x; y += v.y;
			}

			/// Subtract a vector from this vector.
			void operator -= (const JVec2& v)
			{
				x -= v.x; y -= v.y;
			}

			/// Multiply this vector by a scalar.
			void operator *= (float a)
			{
				x *= a; y *= a;
			}

			/// Get the length of this vector (the norm).
			float Length() const
			{
				return std::sqrt(x * x + y * y);
			}

			/// Get the length squared. For performance, use this instead of
			/// b2Vec2::Length (if possible).
			float LengthSquared() const
			{
				return x * x + y * y;
			}

			/// Convert this vector into a unit vector. Returns the length.
			float Normalize()
			{
				float length = Length();
				if (length < FLT_EPSILON)
				{
					return 0.0f;
				}
				float invLength = 1.0f / length;
				x *= invLength;
				y *= invLength;

				return length;
			}

			bool FloatIsValid(float x)
			{
				int ix = *reinterpret_cast<int*>(&x);
				return (ix & 0x7f800000) != 0x7f800000;
			}

			/// Does this vector contain finite coordinates?
			bool IsValid() const
			{
				return false;// FloatIsValid(x) && FloatIsValid(y);
			}

			/// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
			JVec2 Skew() const
			{
				return JVec2(-y, x);
			}

			float x, y;
		};
	}
}

#endif // !JRENDERDEFINES
