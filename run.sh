
#!/usr/bin/env bash

if [ "$(type -t ./build/bin/carol)" = "file" ]; then
    echo -e "\n[INFO]: Running..."
    
    cd ./build/bin/
    
    ./carol
    
    cd ..
else
    echo -e "[FAILED]: Application could not be ran: executable does not exist or contains error(s). \n"
fi
