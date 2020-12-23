//vimrc
noremap <F5> :w <bar> !g++ -DLOCAL -std=c++14 -static -Wall -Wno-unused-result -O2 %:r.cpp -o %:r<CR>
noremap <F6> :w <bar> !g++ -DLOCAL -std=c++14 -static -Wall -Wno-unused-result -O2 %:r.cpp -o %:r && ./%:r<in<CR>
noremap <F9> :<C-U> !./%:r<CR>
set number
set shiftwidth=2
set tabstop=2
set autoindent
set expandtab
//judge
submit() { boca-submit-run TEAM PASSWORD "$1" C++14 "$1.cpp"; }
