#!/bin/bash
cat > .clangd << EOF
CompileFlags:
  Add: [-I${GBDK_HOME}/include, -D__TARGET_gb]
EOF
