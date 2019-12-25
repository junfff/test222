

nnoremap <F2> :NERDTreeToggle<CR>

nnoremap <leader>t tabn
nnoremap == gg=G :w<CR> <C-o> <C-o>
inoremap <A-=> gg=G :w<CR> <C-o> <C-o>
inoremap <F12> <ESC> gg=G :w<CR> <C-o> <C-o> i
nnoremap <F12> <ESC> gg=G :w<CR> <C-o> <C-o>
nnoremap <F4> :set nu
nnoremap <leader>g :

" Vundle keyfire
nnoremap <leader>vi :PlugInstall<CR>
nnoremap <leader>vu :PlugUpdate<CR>

" Split faster
nnoremap <leader>\ :vs<CR>
nnoremap <leader>- :sp<CR>


" Buffers KeyFire
nnoremap <leader>b :Buffers<CR>


" Buftabline Config Manager
nnoremap <C-k> :bnext<CR>
nnoremap <C-j> :bprev<CR>
nnoremap <C-x> :bdelete<CR>

"--------------------------------------------------------------------------------

" Vim-quickhl
nmap <Space>m <Plug>(quickhl-manual-this)
xmap <Space>m <Plug>(quickhl-manual-this)
nmap <Space>M <Plug>(quickhl-manual-reset)
xmap <Space>M <Plug>(quickhl-manual-reset)
