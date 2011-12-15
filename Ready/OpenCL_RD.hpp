/*  Copyright 2011, The Ready Bunch

    This file is part of Ready.

    Ready is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ready is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ready. If not, see <http://www.gnu.org/licenses/>.         */

// local:
#include "UserAlgorithm.hpp"

// OpenCL: (local copy)
#include "cl.hpp"

// base class for those RD implementations that use OpenCL
class OpenCL_RD : public UserAlgorithm
{
    public:

        OpenCL_RD();
        ~OpenCL_RD();
    
        void SetPlatform(int i);
        void SetDevice(int i);
        int GetPlatform();
        int GetDevice();
    
    protected:

        void ReloadContextIfNeeded();
        void ReloadKernelIfNeeded();

        void CreateOpenCLBuffers();
        void WriteToOpenCLBuffers();
        void ReadFromOpenCLBuffers();
        void DeleteOpenCLBuffers();

        void Update2Steps();

    private:
    
        // OpenCL things for re-use
        cl::Context *context;
        cl::CommandQueue *command_queue;
        cl::Device *device;
        cl::Program *program;
        cl::Program::Sources *source;
        cl::Kernel *kernel;
        cl::Buffer *buffer1,*buffer2;
        cl::NDRange global_range,local_range;

        std::string kernel_function_name;

    private:
        
        int iPlatform,iDevice;
        bool need_reload_context;
};

const char* descriptionOfError(cl_int err);