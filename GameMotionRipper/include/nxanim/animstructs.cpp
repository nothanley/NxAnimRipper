#include <animstructs.h>
#pragma once

// Global Defs
uint64_t NX::gTargetTreeHash = NULL;

NX::Vec4 NX::NXMatrix4::rotation_quaternion() const
{
    NX::Vec4 quat;

    // Extract the rotation matrix components
    float m00 = row3.x;  // First row, first column
    float m01 = row3.y;  // First row, second column
    float m02 = row3.z;  // First row, third column
    float m10 = row2.x;  // Second row, first column
    float m11 = row2.y;  // Second row, second column
    float m12 = row2.z;  // Second row, third column
    float m20 = row1.x;  // Third row, first column
    float m21 = row1.y;  // Third row, second column
    float m22 = row1.z;  // Third row, third column

    // Determine which of w, x, y, or z has the largest absolute value
    float trace = m00 + m11 + m22;

    if (trace > 0) {
        float s = sqrt(trace + 1.0f) * 2;  // s = 4 * quat.w
        quat.w = 0.25f * s;
        quat.x = (m21 - m12) / s;
        quat.y = (m02 - m20) / s;
        quat.z = (m10 - m01) / s;
    }
    else if ((m00 > m11) && (m00 > m22)) {
        float s = sqrt(1.0f + m00 - m11 - m22) * 2;  // s = 4 * quat.x
        quat.w = (m21 - m12) / s;
        quat.x = 0.25f * s;
        quat.y = (m01 + m10) / s;
        quat.z = (m02 + m20) / s;
    }
    else if (m11 > m22) {
        float s = sqrt(1.0f + m11 - m00 - m22) * 2;  // s = 4 * quat.y
        quat.w = (m02 - m20) / s;
        quat.x = (m01 + m10) / s;
        quat.y = 0.25f * s;
        quat.z = (m12 + m21) / s;
    }
    else {
        float s = sqrt(1.0f + m22 - m00 - m11) * 2;  // s = 4 * quat.z
        quat.w = (m10 - m01) / s;
        quat.x = (m02 + m20) / s;
        quat.y = (m12 + m21) / s;
        quat.z = 0.25f * s;
    }

    return quat;
}

NX::Vec3 NX::NXMatrix4::translation() const
{
    return Vec3{ row0.x, row0.y, row0.z };
}

std::vector<float> NX::NXMatrix4::to_vector() const
{
	return { row3.x, row3.y, row3.z, row3.w,
			 row2.x, row2.y, row2.z, row2.w,
			 row1.x, row1.y, row1.z, row1.w,
			 row0.x, row0.y, row0.z, row0.w };
}

