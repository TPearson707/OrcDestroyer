g++ src/main.cpp src/Animator.cpp src/AssetManager.cpp src/Game.cpp src/Orc.cpp src/Player.cpp -o main -std=c++17 \
  -I./SFML-3.0.2/include \
  -F./SFML-3.0.2/Frameworks \
  -framework sfml-graphics \
  -framework sfml-window \
  -framework sfml-system \
  -Wl,-rpath,@executable_path/SFML-3.0.2/Frameworks