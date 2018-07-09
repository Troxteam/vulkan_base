glslangvalidator -V shader.vert -o shader.vert.spv
glslangvalidator -V shader.tesc -o shader.tesc.spv
glslangvalidator -V shader.tese -o shader.tese.spv
glslangvalidator -V shader.frag -o shader.frag.spv
pause
glslangvalidator -V shader-pass.vert -o shader-pass.vert.spv
glslangvalidator -V shader-pass.tesc -o shader-pass.tesc.spv
glslangvalidator -V shader-pass.tese -o shader-pass.tese.spv
glslangvalidator -V shader-pass.frag -o shader-pass.frag.spv
pause
