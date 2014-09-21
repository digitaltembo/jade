/****************************************************************************
 *   Last Modified: 7/28                                                    *
 *   Compilation Flags: -lOpenCL                                            *
 *                                                                          *
 *   Links:                                                                 *
 *   Intel Installation:                                                    *
 *      https://software.intel.com/en-us/vcsource/tools/opencl-sdk          *
 *   Installation instructions:                                             *
 *      https://gist.github.com/rmcgibbo/6314452                            *
 *   Specifications:                                                        *
 *      http://www.khronos.org/registry/cl/specs/opencl-cplusplus-1.2.pdf   *
 *   Reference card:                                                        *
 *      https://www.khronos.org/files/OpenCLPP12-reference-card.pdf         *
 *   More stuff: (my version is 1.2)                                        *
 *      https://www.khronos.org/registry/cl/                                *
 *                                                                          *
 *   And further helping hands:                                             *
 *      http://www.thebigblob.com/using-the-cpp-bindings-for-opencl/        *
 ****************************************************************************/

#ifndef MY_OPENCL
#define MY_OPENCL

#define __NO_STD_VECTOR
#include <CL/cl.hpp>
class OpenCL{
    OpenCL();
   ~OpenCL();
};

#endif

