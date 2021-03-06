/**
 * Copyright (C) 2019 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop-
 * ies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM-
 * PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNE-
 * CTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <Tensile/Tensile.hpp>
#include <Tensile/TensorOps_fwd.hpp>
#include <Tensile/TensorDescriptor_fwd.hpp>

namespace Tensile
{

    using TensorOps = std::vector<TensorOp>;

    /**
     * Represents a tensor operation that can be performed inline to a kernel.  For now can represent
     * a complex conjugate but this could be where we represent inline activation layers
     * later.
     */
    class TENSILE_API TensorOp
    {
    public:

        enum class Type: int
        {
            None,
            ComplexConjugate,
            Count
        };

        Type type = Type::None;

        TensorOp();
        TensorOp(Type type);

        static TensorOp ComplexConjugate() { return TensorOp(Type::ComplexConjugate); }

        // static TensorOp ReLU();
        // static TensorOp LeakyReLU(float alpha);
        // ...

        bool operator==(TensorOp const& rhs) const { return this->type == rhs.type; }
        bool operator< (TensorOp const& rhs) const { return this->type < rhs.type; }

        bool operator> (TensorOp const& rhs) const { return rhs < *this; }
        bool operator!=(TensorOp const& rhs) const { return !(*this == rhs); }
        bool operator<=(TensorOp const& rhs) const { return !(*this > rhs); }
        bool operator>=(TensorOp const& rhs) const { return !(*this < rhs); }
    };
}
