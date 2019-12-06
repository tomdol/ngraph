//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/op/util/binary_elementwise_arithmetic.hpp"

namespace ngraph
{
    namespace op
    {
        namespace v0
        {
            /// \brief Elementwise minimum operation.
            class NGRAPH_API Minimum : public util::BinaryElementwiseArithmetic
            {
            public:
                static constexpr NodeTypeInfo type_info{"Minimum", 0};
                const NodeTypeInfo& get_type_info() const override { return type_info; }
                /// \brief Constructs a minimum operation.
                Minimum()
                    : util::BinaryElementwiseArithmetic(AutoBroadcastSpec::NONE)
                {
                }
                /// \brief Constructs a minimum operation.
                ///
                /// \param arg0 Node that produces the first input tensor.
                /// \param arg1 Node that produces the second input tensor.
                /// \param auto_broadcast Auto broadcast specification
                Minimum(const Output& arg0,
                        const Output& arg1,
                        const AutoBroadcastSpec& auto_broadcast = AutoBroadcastSpec());

                virtual std::shared_ptr<Node>
                    copy_with_new_args(const NodeVector& new_args) const override;

                virtual bool is_commutative() const override { return true; }
            protected:
                virtual void generate_adjoints(autodiff::Adjoints& adjoints,
                                               const NodeVector& deltas) override;
            };
        } // namespace v0

        namespace v1
        {
            /// \brief Elementwise minimum operation.
            class NGRAPH_API Minimum : public util::BinaryElementwiseArithmetic
            {
            public:
                static constexpr NodeTypeInfo type_info{"Minimum", 1};
                const NodeTypeInfo& get_type_info() const override { return type_info; }
                /// \brief Constructs a minimum operation.
                Minimum()
                    : util::BinaryElementwiseArithmetic(AutoBroadcastSpec::NUMPY)
                {
                }

                /// \brief Constructs a minimum operation.
                ///
                /// \param arg0 Node that produces the first input tensor.
                /// \param arg1 Node that produces the second input tensor.
                /// \param auto_broadcast Auto broadcast specification
                Minimum(const Output& arg0,
                        const Output& arg1,
                        const AutoBroadcastSpec& auto_broadcast =
                            AutoBroadcastSpec(AutoBroadcastType::NUMPY));

                virtual std::shared_ptr<Node>
                    copy_with_new_args(const NodeVector& new_args) const override;

                virtual bool is_commutative() const override { return true; }
                size_t get_version() const override { return 1; }
            protected:
                virtual void generate_adjoints(autodiff::Adjoints& adjoints,
                                               const NodeVector& deltas) override;
            };
        } // namespace v1

        using v0::Minimum;
    }
}
