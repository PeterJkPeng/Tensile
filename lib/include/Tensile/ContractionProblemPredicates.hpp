/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#pragma once

#include <Tensile/Predicates.hpp>
#include <Tensile/ContractionProblem.hpp>

#include <array>
#include <vector>

namespace Tensile
{
    namespace Predicates
    {
        namespace Contraction
        {
            struct FreeSizeAMultiple: public Predicate_CRTP<FreeSizeAMultiple, ContractionProblem>
            {
                enum { HasIndex = true, HasValue = true };
                size_t index;
                size_t value;

                FreeSizeAMultiple() = default;
                FreeSizeAMultiple(size_t index, size_t value): index(index), value(value) {}

                static std::string Type() { return "FreeSizeAMultiple"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.freeSizeA(index) % value == 0;
                }
            };

            struct FreeSizeBMultiple: public Predicate_CRTP<FreeSizeBMultiple, ContractionProblem>
            {
                enum { HasIndex = true, HasValue = true };
                size_t index;
                size_t value;

                FreeSizeBMultiple() = default;
                FreeSizeBMultiple(size_t index, size_t value): index(index), value(value) {}

                static std::string Type() { return "FreeSizeBMultiple"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.freeSizeA(index) % value == 0;
                }
            };

            struct BatchSizeMultiple: public Predicate_CRTP<BatchSizeMultiple, ContractionProblem>
            {
                enum { HasIndex = true, HasValue = true };
                size_t index;
                size_t value;

                BatchSizeMultiple() = default;
                BatchSizeMultiple(size_t index, size_t value): index(index), value(value) {}

                static std::string Type() { return "BatchSizeMultiple"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.batchSize(index) % value == 0;
                }
            };

            struct BoundSizeMultiple: public Predicate_CRTP<BoundSizeMultiple, ContractionProblem>
            {
                enum { HasIndex = true, HasValue = true };
                size_t index;
                size_t value;

                BoundSizeMultiple() = default;
                BoundSizeMultiple(size_t index, size_t value): index(index), value(value) {}

                static std::string Type() { return "BoundSizeMultiple"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.boundSize(index) % value == 0;
                }
            };

            struct MaxProblemSizeGreaterThan: public Predicate_CRTP<MaxProblemSizeGreaterThan, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = true };
                size_t value;

                MaxProblemSizeGreaterThan() = default;
                MaxProblemSizeGreaterThan(size_t value): value(value) {}

                static std::string Type() { return "MaxProblemSizeGreaterThan"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.maxProblemSize() > value;
                }
            };

            struct LeadingSizesGreaterOrEqual: public Predicate_CRTP<LeadingSizesGreaterOrEqual, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = true };
                size_t value;

                LeadingSizesGreaterOrEqual() = default;
                LeadingSizesGreaterOrEqual(size_t value): value(value) {}

                static std::string Type() { return "LeadingSizesGreaterOrEqual"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.a().sizes()[0] >= value
                        && problem.b().sizes()[0] >= value
                        && problem.c().sizes()[0] >= value
                        && problem.d().sizes()[0] >= value;
                }
            };

            struct CDStridesEqual: public Predicate_CRTP<CDStridesEqual, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = false };
                static std::string Type() { return "CDStridesEqual"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.c().strides() == problem.d().strides();
                }
            };

            struct LDCEqualsLDD: public Predicate_CRTP<LDCEqualsLDD, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = false };
                static std::string Type() { return "LDCEqualsLDD"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.c().strides()[1] == problem.d().strides()[1];
                }
            };

            struct BetaZero: public Predicate_CRTP<BetaZero, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = false };
                BetaZero() = default;

                static std::string Type() { return "BetaZero"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.beta() == 0.0;
                }
            };

            struct BetaOne: public Predicate_CRTP<BetaOne, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = false };
                BetaOne() = default;

                static std::string Type() { return "BetaOne"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.beta() == 1.0;
                }
            };

            struct TypesEqual: public Predicate_CRTP<TypesEqual, ContractionProblem>
            {
                enum { HasIndex = false, HasValue = true };
                TypesEqual() = default;

                std::array<DataType, 4> value;

                static std::string Type() { return "TypesEqual"; }

                virtual bool operator()(ContractionProblem const& problem) const override
                {
                    return problem.a().dataType() == value[0]
                        && problem.b().dataType() == value[1]
                        && problem.c().dataType() == value[2]
                        && problem.d().dataType() == value[3];
                }

                virtual std::string toString() const override
                {
                    return concatenate(this->type(),
                                       "(a:",  value[0],
                                       ", b:", value[1],
                                       ", c:", value[2],
                                       ", d:", value[3],
                                       ")");
                }

                virtual bool debugEval(ContractionProblem const& problem, std::ostream & stream) const override
                {
                    bool rv = (*this)(problem);

                    stream << this->type()
                           <<   "(a:" << problem.a().dataType() << " == " << value[0]
                           << "&& b:" << problem.b().dataType() << " == " << value[1]
                           << "&& c:" << problem.c().dataType() << " == " << value[2]
                           << "&& d:" << problem.d().dataType() << " == " << value[3]
                           << "): " << rv;

                    return rv;
                }
            };

        }
    }
}

