/*
 * Copyright (c) 2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
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
 */
#ifndef __ARM_COMPUTE_GRAPH_TYPES_H__
#define __ARM_COMPUTE_GRAPH_TYPES_H__

#include "arm_compute/core/Error.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/core/utils/strong_type/StrongType.h"
#include "arm_compute/core/utils/strong_type/StrongTypeAttributes.h"

#include <limits>
#include <string>

namespace arm_compute
{
namespace graph
{
using arm_compute::Status;

using arm_compute::Coordinates;
using arm_compute::DataType;
using arm_compute::DataLayout;
using arm_compute::DataLayoutDimension;
using arm_compute::TensorShape;
using arm_compute::Size2D;

using arm_compute::ActivationLayerInfo;
using arm_compute::NormType;
using arm_compute::NormalizationLayerInfo;
using arm_compute::PadStrideInfo;
using arm_compute::PoolingLayerInfo;
using arm_compute::PoolingType;
using arm_compute::DimensionRoundingType;

using TensorID   = unsigned int;
using NodeID     = unsigned int;
using EdgeID     = unsigned int;
using Activation = arm_compute::ActivationLayerInfo::ActivationFunction;

/**< GraphID strong type */
using GraphID = strong_type::StrongType<unsigned int, struct graph_id_t, strong_type::Comparable>;

/**< Constant TensorID specifying an equivalent of null tensor */
constexpr TensorID NullTensorID = std::numeric_limits<TensorID>::max();
/**< Constant NodeID specifying an equivalent of null node */
constexpr NodeID EmptyNodeID = std::numeric_limits<NodeID>::max();
/**< Constant EdgeID specifying an equivalent of null edge */
constexpr EdgeID EmptyEdgeID = std::numeric_limits<EdgeID>::max();

// Forward declarations
class TensorDescriptor;

/** Graph configuration structure */
struct GraphConfig
{
    bool use_function_memory_manager{ true };   /**< Use a memory manager to manage per-funcion auxilary memory */
    bool use_transition_memory_manager{ true }; /**< Use a memory manager to manager transition buffer memory */
    bool use_tuner{ false };                    /**< Use a tuner in tunable backends */
    int  num_threads{ -1 };                     /**< Number of threads to use (thread capable backends), if 0 the backend will auto-initialize, if -1 the backend will stay as it is. */
};

/**< Device target types */
enum class Target
{
    UNSPECIFIED, /**< Unspecified Target */
    NEON,        /**< NEON capable target device */
    CL,          /**< OpenCL capable target device */
    GC,          /**< GLES compute capable target device */
};

/** Supported Element-wise operations */
enum class EltwiseOperation
{
    ADD, /**< Arithmetic addition */
    SUB, /**< Arithmetic subtraction */
    MUL  /**< Arithmetic multiplication */
};

/** Supported Convolution layer methods */
enum class ConvolutionMethod
{
    DEFAULT, /**< Default approach using internal heuristics */
    GEMM,    /**< GEMM based convolution */
    DIRECT,  /**< Deep direct convolution */
    WINOGRAD /**< Winograd based convolution */
};

/** Supported Depthwise Convolution layer methods */
enum class DepthwiseConvolutionMethod
{
    DEFAULT,       /**< Default approach using internal heuristics */
    GEMV,          /**< Generic GEMV based depthwise convolution */
    OPTIMIZED_3x3, /**< Optimized 3x3 direct depthwise convolution */
};

/** Enable or disable fast math for Convolution layer */
enum class FastMathHint
{
    ENABLED,  /**< Fast math enabled for Convolution layer */
    DISABLED, /**< Fast math disabled for Convolution layer */
};

/** Supported nodes */
enum class NodeType
{
    ActivationLayer,
    BatchNormalizationLayer,
    ConvolutionLayer,
    DepthConcatenateLayer,
    DepthwiseConvolutionLayer,
    EltwiseLayer,
    FlattenLayer,
    FullyConnectedLayer,
    NormalizationLayer,
    PoolingLayer,
    ReshapeLayer,
    ScaleLayer,
    SoftmaxLayer,
    SplitLayer,

    Input,
    Output,
    Const,
};

/** Backend Memory Manager affinity **/
enum class MemoryManagerAffinity
{
    Buffer, /**< Affinity at buffer level */
    Offset  /**< Affinity at offset level */
};

/** NodeID-index struct
 *
 * Used to describe connections
 */
struct NodeIdxPair
{
    NodeID node_id; /**< Node ID */
    size_t index;   /**< Index */
};

/** Common node parameters */
struct NodeParams
{
    std::string name;   /**< Node name */
    Target      target; /**< Node target */
};
} // namespace graph
} // namespace arm_compute
#endif /* __ARM_COMPUTE_GRAPH_TYPES_H__ */
