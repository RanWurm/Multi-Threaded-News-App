#include "./data_handler/data_handler.h"
#include "./news_runner/news_runner.h"
char* file_path_text = "/home/ran/Desktop/newsApp/config.txt";
int main(int argc, char* argv[]) {
    int prods_size = 0;
    int* prods = read_product_numbers(argv[1],&prods_size );
    int buffs_size = 0;
    int* buffs = read_queue_sizes(argv[1], &buffs_size);
   run(prods,buffs,prods_size );
return 0;
}
