










" Format
set nu
set copyindent
set preserveindent
set tabstop=4 "4
set shiftwidth=4 "4
set softtabstop=4 "4
" set expandtab
set noexpandtab


set autochdir

"autocmd FileType makefile set noexpandtab 试了这一条，没有起作用
autocmd FileType make set noexpandtab "这一条最终起作用了

set autoindent
set cindent
