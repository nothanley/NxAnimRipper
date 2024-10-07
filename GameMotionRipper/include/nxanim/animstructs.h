#include <cmath>
#include <algorithm>
#include <vector>
#pragma once

namespace NX
{
	// Global settings
	extern uint64_t gTargetTreeHash;

	// Animation and data structures
	struct Vec3 {
		float x, y, z;

		void pack_values(float ceiling) {
			x = (x > ceiling) ? ceiling : x;
			y = (x > ceiling) ? ceiling : y;
			z = (x > ceiling) ? ceiling : z;

			float floor = -ceiling;
			x = (x < floor) ? floor : x;
			y = (x < floor) ? floor : y;
			z = (x < floor) ? floor : z;
		}

		void operator*=(float value) {
			x *= value;
			y *= value;
			z *= value;
		}

		void operator/=(float value) {
			x /= value;
			y /= value;
			z /= value;
		}

		void operator+=(const Vec3& value) {
			x += value.x;
			y += value.y;
			z += value.z;
		}

		Vec3 operator*(float value) {
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		Vec3 operator*(float s) const
		{
			Vec3 v = *this;
			return v * s;
		}

		Vec3 operator+(const Vec3& other) const {
			return Vec3{ x + other.x, y + other.y, z + other.z };
		}

		Vec3 operator-(const Vec3& other) const {
			return Vec3{ x - other.x, y - other.y, z - other.z };
		}

		bool operator==(const Vec3& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		bool operator!=(const Vec3& other) const {
			return (x != other.x) || (y != other.y) || (z != other.z);
		}


		static void min(Vec3& result, const Vec3& a, const Vec3& b)
		{
			result.x = std::isnan(a.x) || std::isnan(b.x) ? result.x : std::min(a.x, b.x);
			result.y = std::isnan(a.y) || std::isnan(b.y) ? result.y : std::min(a.y, b.y);
			result.z = std::isnan(a.z) || std::isnan(b.z) ? result.z : std::min(a.z, b.z);
		};

		static void max(Vec3& result, const Vec3& a, const Vec3& b)
		{
			result.x = std::isnan(a.x) || std::isnan(b.x) ? result.x : std::max(a.x, b.x);
			result.y = std::isnan(a.y) || std::isnan(b.y) ? result.y : std::max(a.y, b.y);
			result.z = std::isnan(a.z) || std::isnan(b.z) ? result.z : std::max(a.z, b.z);
		};

		void handleNaN(float value = 0.00001f) {
			if (std::isnan(x)) x = value;
			if (std::isnan(y)) y = value;
			if (std::isnan(z)) z = value;
		}

		void normalize() {
			float length = std::sqrt(x * x + y * y + z * z);
			if (length != 0.0f) {
				x /= length;
				y /= length;
				z /= length;
			}
		}

		bool null() const {
			return x == 0 && y == 0 && z == 0;
		}

		static Vec3 cross(const Vec3& a, const Vec3& b) {
			return  Vec3{ a.y * b.z - a.z * b.y,
					  a.z * b.x - a.x * b.z,
					  a.x * b.y - a.y * b.x };
		}

		static float dot(const Vec3& a, const Vec3& b) {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}
	};

	struct Vec2 {
		float x, y;

		Vec2 operator-(const Vec2& other) const {
			return Vec2{ x - other.x, y - other.y };
		}

		operator Vec3() const
		{
			return Vec3{ x, y, 0.0f };
		}
	};

	struct Vec4 {
		float x, y, z, w;

		Vec4() : x(0), y(0), z(0), w(0) {}
		Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	};

	struct KeyFrame 
	{
		Vec4   transform;
		uint8_t duration;
	};




	// NEW STRUCTS - NXRipper
	struct NXMatrix4
	{
		NX::Vec4 row3;
		NX::Vec4 row2;
		NX::Vec4 row1;
		NX::Vec4 row0;

		std::vector<float> to_vector() const;
		NX::Vec4 rotation_quaternion() const;
		NX::Vec3 translation() const;
	};
}



