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

#include <cstdarg>
#include "mlir/IR/Builders.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/IR/StandardTypes.h"
#include "mlir/Support/STLExtras.h"

namespace ngraph
{
    namespace runtime
    {
        namespace ngmlir
        {
            // TODO: We shouldn't have this here, but we need to expose mlir types for the .inc file to use
            // we cannot forward declare the mlir types since they rely on the Ops we are defining (see. Op<NGAddOp, ...>)
            //
            // Other ways to avoid namespace pollution ?
            using namespace mlir;
#define GET_OP_CLASSES
#include "ops.h.inc"
        }
    }
}