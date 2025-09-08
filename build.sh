
#!/usr/bin/env -eu

echo -e "[CONFIG]: Are you generating ninja files? (y or n)(DEFAULT: n)"
read -p " > " build
echo -e "[CONFIG]: Do you want to run the project right after building it? (y or n)(DEFAULT: y)"
read -p " > " run

echo -e "[INFO]: Creating build folder if not exists..."
mkdir -p ./build && cd ./build

if [ "$build" = "y" ]; then
    echo -e "[INFO]: Generating Ninja files..."
    cmake .. -G Ninja
fi

echo -e "[INFO]: Building..."
ninja

cd ..

if  [ "$run" != "n" ]; then
    echo -e "\n--------------------------------------------------"
    ./run.sh
fi

