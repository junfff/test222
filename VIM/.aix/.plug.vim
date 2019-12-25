" ========================= Aix Plug Manager =========================
" Vim-Plug update Manager
" * Expert Vundle Plugin Manager
filetype off

" # Plugins Beginning
call plug#begin('~/.vim/bundle/')

Plug 'scrooloose/nerdtree'
Plug 'Xuyuanp/nerdtree-git-plugin'

Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }
Plug 'junegunn/fzf.vim'
Plug 'junegunn/gv.vim'
Plug 'tweekmonster/fzf-filemru'


" @ Plugin --- [ Code Complete Unity ]
Plug 'Valloric/YouCompleteMe'
Plug 'mattn/emmet-vim'
Plug 'SirVer/ultisnips'
Plug 'letientai299/vim-react-snippets', { 'branch': 'es6' }
Plug 'honza/vim-snippets'
Plug 'Shougo/vimproc', { 'do': 'make' }
Plug 'Shougo/neoinclude.vim'
Plug 'Shougo/neco-vim'
Plug 'Shougo/neco-syntax'
"Plug 'ternjs/tern_for_vim', { 'do': 'npm install' }



Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

Plug 'Chiel92/vim-autoformat'
Plug 'majutsushi/tagbar'
Plug 'Valloric/ListToggle'

Plug 't9md/vim-quickhl'
Plug 'scrooloose/nerdcommenter'

" ---- Plug List Complete ----
call plug#end()

syntax on
syntax enable

filetype on
filetype plugin on
filetype plugin indent on
" ========================= Plug Setup End =========================
