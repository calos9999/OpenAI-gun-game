#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

const int MAX_BULLETS = 6;
const int MAX_ENEMIES = 3;

class Bullet {
 public:
  Bullet() : damage_(10) {}

  int getDamage() const { return damage_; }

 private:
  int damage_;
};

class Gun {
 public:
  Gun(int maxBullets) : bullets_(maxBullets), maxBullets_(maxBullets) {}

  int getNumBullets() const { return bullets_; }
  void shoot() { bullets_--; }
  void reload() {
    std::cout << "Reloading..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bullets_ = maxBullets_;
    std::cout << "Your gun has been reloaded!" << std::endl;
  }

 private:
  int bullets_;
  int maxBullets_;
};

class Player {
 public:
  Player() : health_(100), gun_(Gun(MAX_BULLETS)) {}

  int getHealth() const { return health_; }
  Gun& getGun() { return gun_; }

  void takeDamage(int damage) { health_ -= damage; }

  bool isAlive() const { return health_ > 0; }
  bool hasBullets() const { return gun_.getNumBullets() > 0; }

 private:
  int health_;
  Gun gun_;
};

int main() {
  srand(time(NULL));

  Player player;
  int enemies = MAX_ENEMIES;
  bool gameOver = false;

  while (player.isAlive() && enemies > 0 && !gameOver) {
    std::cout << "Bullets: " << player.getGun().getNumBullets() << std::endl;
    std::cout << "Enemies: " << enemies << std::endl;
    std::cout << "Health: " << player.getHealth() << std::endl;

    std::cout << "Enter a command (shoot, reload, exit): ";
    std::string command;
    std::cin >> command;

    if (command == "shoot") {
      if (player.hasBullets()) {
        player.getGun().shoot();

        if (rand() % 2 == 0) {
          enemies--;
          std::cout << "You hit an enemy!" << std::endl;
        } else {
          std::cout << "You missed!" << std::endl;
        }
      } else {
        std::cout << "You don't have any bullets left!" << std::endl;
      }
    } else if (command == "reload") {
      if (!player.hasBullets()) {
                player.getGun().reload();
      } else {
        std::cout << "Your gun is already full!" << std::endl;
      }
    } else if (command == "exit") {
      std::cout << "Thanks for playing, Made with chatGPT on 12/23/2022" << std::endl;
      gameOver = true;
      break;
    } else {
      std::cout << "Invalid command" << std::endl;
    }

    if (enemies > 0) {
      int damage = rand() % 10 + 10;
      std::cout << "An enemy attack you for " << damage << " damage!" << std::endl;
      player.takeDamage(damage);
    }
  }

  if (!player.isAlive()) {
    std::cout << "You have been killed by the enemies!" << std::endl;
  } else if (!gameOver) {
    std::cout << "You have defeated all of the enemies!" << std::endl;
  }

  return 0;
}
