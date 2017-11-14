# INSTALAÇÃO ALLEGRO 5 LINUX

    sudo apt-get install build-essential subversion cmake xorg-dev libgl1-mesa-dev libglu-dev
    
    sudo apt-get install libpng-dev libz-dev libcurl4-gnutls-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev libasound-dev libflac-dev libdumb1-dev
    
    sudo apt-get install exuberant-ctags dvi2ps dvipdfmx latex2html pandoc
    
    svn co https://alleg.svn.sourceforge.net/svnroot/alleg/allegro/branches/5.0 allegro-5.0

# COMPILAÇÃO ALLEGRO5
    cd allegro-5.0

    cmake -DCMAKE_INSTALL_PREFIX=/usr .
    
    make
 
    sudo make install

# BAIXAR E COMPILAR O JOGO NA SUA MAQUINA:
    git clone https://github.com/tarcisio-marinho/allegro.git

    cd allegro

    sh comp.sh

# SEMPRE QUE QUISER JOGAR O JOGO:

    ./main