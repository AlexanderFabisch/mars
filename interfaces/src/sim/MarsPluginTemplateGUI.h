/*
 *  Copyright 2014, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MARS_PLUGIN_TEMPLATE_GUI_H
#define MARS_PLUGIN_TEMPLATE_GUI_H

#include "ControlCenter.h"
#include "../MARSDefs.h"
#include "PluginInterface.h"
#include "SimulatorInterface.h"

#include <mars/utils/Singleton.hpp>
#include <mars/cfg_manager/CFGManagerInterface.h>

#include <string>

#include <mars/main_gui/GuiInterface.h>

namespace mars {
  namespace interfaces {

    class MarsPluginTemplateGUI : public singleton::Interface,
                               public PluginInterface {

    public:
  
      MarsPluginTemplateGUI(std::string libName) : 
        PluginInterface(NULL), mars(NULL) {

        singleton::Interface *lib;
        //lib = libManager->getLibrary("mars_sim"); //TODO
        pluginStruct newplugin;
        if(lib) {
          if( (mars = dynamic_cast<SimulatorInterface*>(lib)) ) {
            control = mars->getControlCenter();
            newplugin.name = libName;
            newplugin.p_interface = dynamic_cast<PluginInterface*>(this);
            newplugin.p_destroy = 0;
      
            if(control->cfg) {
              cfg_manager::cfgPropertyStruct cfgPath;
              cfgPath = control->cfg->getOrCreateProperty("Preferences",
                                                          "resources_path",
                                                          std::string("."));
          
              resourcesPath = cfgPath.sValue;

              cfgPath = control->cfg->getOrCreateProperty("Config",
                                                          "config_path",
                                                          std::string("."));
      
              configPath = cfgPath.sValue;
            }
          }
        }

//        gui = libManager->getLibraryAs<main_gui::GuiInterface>("main_gui"); //TODO
        // this part should be the last line of the contructor
        // we can get a timing problem if mars want to use the
        // plugin before the contructor is finished -> so the last part here
        // is to register the plugin to mars
        if(mars) mars->addPlugin(newplugin);
      }

      ~MarsPluginTemplateGUI() {
//        if(mars) libManager->releaseLibrary("mars_sim"); //TODO
//        if(gui) libManager->releaseLibrary("main_gui"); //TODO
      }

      private:
        SimulatorInterface *mars;

      protected:
        std::string configPath;
        std::string resourcesPath;
        main_gui::GuiInterface *gui;
      };

  } // end of namespace interfaces
} // end of namespace mars

#endif // MARS_PLUGIN_TEMPLATE_GUI_H
