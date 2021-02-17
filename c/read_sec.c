#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
  int i;
  int descriptor;
  struct stat stat;
  char *head; // 1byteずつ読み出すための変数
  Elf64_Ehdr* elf_header; // ELFヘッダ
  Elf64_Shdr* shstrtab_header; // セクションヘッダ1つ分の構造体(今回はセクション名を格納しているセクションのヘッダを入れる)
  Elf64_Shdr* tmp_section_header;

  descriptor = open("./hello", O_RDONLY);
  fstat(descriptor, &stat);
  printf("descriptor = %d\n", descriptor);
  printf("st_dev= %lu\n", stat.st_dev);
  printf("st_size= %lu\n", stat.st_size);

  head = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, descriptor, 0);
  elf_header = (Elf64_Ehdr*) head; // elfファイルの先頭のアドレスをEhdrに参照させてヘッダ情報を読み出す
  // 1) head + e_shoff = セクションヘッダの先頭のアドレス
  // 2) elf_header->e_shentsize * elf_header->e_shstrndx = shstrtabのヘッダ情報の先頭アドレスへのオフセット
  // 1 + 2でshstrtabのヘッダ情報の先頭アドレス
  shstrtab_header = (Elf64_Shdr*) ((head + elf_header->e_shoff) + (elf_header->e_shentsize * elf_header->e_shstrndx));

  for(i = 0; i < elf_header->e_shnum; i++) {
    tmp_section_header = (Elf64_Shdr*) ((head + elf_header->e_shoff) + (elf_header->e_shentsize * i));
    // shstrtabの先頭アドレスからsh_name(先頭のオフセット)を足してセクション名を取得
    printf("%s,  %ld\n",
        (head + shstrtab_header->sh_offset + tmp_section_header->sh_name),
        tmp_section_header->sh_entsize
        );
  }

  munmap(head, stat.st_size);
  close(descriptor);
  return 0;
}
