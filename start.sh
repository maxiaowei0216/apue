#! /bin/sh

mkdir build
cd ./build
# rm -r *
cmake ..
# 检查cmake是否错误
if [ $? -eq 0 ]
then
    make
    # 检查make是否错误
    if [ $? -eq 0 ]
    then
        ./bin/exc
    else
        echo "make error"
    fi
else
    echo "cmake error"
fi