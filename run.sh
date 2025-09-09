
#!/usr/bin/env bash

if [ -f ./build/bin/carol ]; then
    echo "\n[INFO]: RUNNING..."
    
    cd ./build/bin/
    
    ./carol
    
    cd ..
else
    echo "[ERROR]: COULD NOT RUN ENGINE: EXECUTABLE DOES NOT EXIST OR HAS SOME ERROR. \n"
fi
