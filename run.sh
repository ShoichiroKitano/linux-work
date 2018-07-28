src_dir=$(pwd)
docker run -it -v $src_dir/source:/source nasm bash
