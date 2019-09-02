// Copyright 2018 The AITS DNNC Authors.All Rights Reserved.
//
// Licensed to the Apache Software Foundation(ASF) under one
// or more contributor license agreements.See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.See the License for the
// specific language governing permissionsand limitations
// under the License.
//
// This file is part of AITS DNN compiler maintained at
// https://github.com/ai-techsystems/dnnCompiler
//

#pragma once
#include "operators/baseOperator.h"
#include <string>

using namespace Eigen;

namespace dnnc {
template <typename T> class DequantizeLinear : public baseOperator<T> {
public:
  DequantizeLinear(std::string name = "opDequantizeLinear")
      : baseOperator<T>(opDequantizeLinear, name) {}

  /*
  static T dequantize_linear_function (T a, float a_scale, float a_zero_point) {
    return ((a - a_zero_point) * a_scale);
  }

  static bool compare(tensor<T> &a, tensor<T> &x_zero_point) {
    return ((typeid(a) == typeid(int)) && (typeid(x_zero_point) == typeid(int)));
  }
  */

  tensor<T> compute(tensor<T> &a, tensor<T> &x_scale, tensor<T> &x_zero_point) {
    if (x_scale.shape() != x_zero_point.shape())
      throw std::invalid_argument(
          "tensor dimenions not appropriate for DequantizeLinear operator.");
     /*
     if (!compare(a,a_zero_point))
      throw std::invalid_argument(
          "Constrain input and output types to float tensors.");
    */
    
    tensor<T> result(a.shape(), a.name());

    for (size_t i = 0; i < a.length(); i++)
      result[i] = (a[i] - x_zero_point[0]) * x_scale[0];
    
    /*
    float a_zero_point = x_zero_point[0];
    float a_scale = x_scale[0];
    a.flatteninplace();
    DNNC_EIGEN_VECTOR(eigenVector, a);
    DNNC_EIGEN_VECTOR_CTOR(T) eResult;
    auto c0 = std::bind(dequantize_linear_function, std::placeholders::_2, a_scale, a_zero_point);
    eResult.array() = eigenVector.array().unaryExpr(c0);
    result.load(eResult.data());
    */

    return result;
  }
};
} // namespace dnnc