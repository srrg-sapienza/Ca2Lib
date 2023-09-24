// clang-format off

// Copyright (c) 2023, S(apienza) R(obust) R(obotics) G(roup)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// clang-format on

#pragma once
#include "target_base.h"
#include <opencv2/aruco/charuco.hpp>

namespace ca2lib {
/**
 * @brief ChArUco calibration target.
 *
 */
class TargetCharuco : public TargetBase {
 public:
  /**
   * @brief Construct a new Target Charuco object
   *
   * @param rows_ number of chessboard squares in X direction
   * @param cols_ number of chessboard squares in Y direction
   * @param len_square_ chessboard square side length (normally in meters)
   * @param len_marker_ marker side length (same unit than len_square)
   * @param family_ dictionary of markers indicating the type of markers.
   */
  using Family_t = cv::aruco::PREDEFINED_DICTIONARY_NAME;
  TargetCharuco(unsigned int rows_, unsigned int cols_, float len_square_,
                float len_marker_, const Family_t family_);

  /**
   * @brief Attempts target detection on the input image. In case target is
   * detected, stores detection parameters internally.
   *
   * @param frame_ Input image
   * @return true if target is detected
   * @return false if target is not detected
   */
  bool detect(const cv::Mat& frame_) override;

  /**
   * @brief Attempts target detection on the input image and estimates relative
   * target position estimate. In case target is detected, stores detection and
   * relative pose parameters internally.
   *
   * @param frame_ Input image
   * @param K_ 3x3 Camera matrix (CV_32F or CV_64F)
   * @param dist_coeffs_ 1xM distortion parameters (CV_32 or CV_64F)
   * @return true if target is detected
   * @return false if target is not detected
   */
  bool detectAndCompute(const cv::Mat& frame_, const cv::Mat& K_,
                        const cv::Mat& dist_coeffs_) override;

  /**
   * @brief Draw the detected target in frame
   *
   * @param frame_ Output image (CV_8UC1 or CV_8UC3)
   */
  void drawDetection(cv::Mat& frame_) const override;

  /**
   * @brief Returns a pointer to the aurco detector parameters
   *
   * @return cv::Ptr<cv::aruco::DetectorParameters>
   */
  inline cv::Ptr<cv::aruco::DetectorParameters> detectorParameters() {
    return _parameters;
  }

 protected:
  cv::Ptr<cv::aruco::CharucoBoard> _board;
  cv::Ptr<cv::aruco::DetectorParameters> _parameters;
};
}  // namespace ca2lib