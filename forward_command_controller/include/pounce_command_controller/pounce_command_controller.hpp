// Copyright 2023 TODO: Wrock
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

#ifndef POUNCE_COMMAND_CONTROLLER__POUNCE_COMMAND_CONTROLLER_HPP_
#define POUNCE_COMMAND_CONTROLLER__POUNCE_COMMAND_CONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>

#include "pounce_command_controller/pounce_controllers_base.hpp"
#include "pounce_command_controller/visibility_control.h"
#include "pounce_command_controller_parameters.hpp"

namespace pounce_command_controller
{
/**
 * \brief Pounce command controller for pounce message.
 *
 * This class forwards the command signal for a set of joints and interfaces.
 *
 * \param joints Names of the joints to control.
 * \param interface_names Names of the interfaces to command.
 *
 * Subscribes to:
 * - \b commands (pounce_msgs::msg::JointCommands) : The commands to apply.
 */
class PounceCommandController : public PounceControllersBase
{
public:
  POUNCE_COMMAND_CONTROLLER_PUBLIC
  PounceCommandController();

protected:
  void declare_parameters() override;
  controller_interface::CallbackReturn read_parameters() override;


  using ParamListener = pounce_command_controller::ParamListener;

  std::shared_ptr<ParamListener> param_listener_;
  Params params_;
};

}  // namespace pounce_command_controller

#endif  // POUNCE_COMMAND_CONTROLLER__POUNCE_COMMAND_CONTROLLER_HPP_
