import random
import time

MAX_BULLETS = 6
MAX_ENEMIES = 3

class Bullet:
    def __init__(self):
        self.damage = 10

    def get_damage(self):
        return self.damage

class Gun:
    def __init__(self, max_bullets):
        self.bullets = max_bullets
        self.max_bullets = max_bullets

    def get_num_bullets(self):
        return self.bullets

    def shoot(self):
        self.bullets -= 1

    def reload(self):
        print("Reloading...")
        time.sleep(1)
        self.bullets = self.max_bullets
        print("Your gun has been reloaded!")

class Player:
    def __init__(self):
        self.health = 100
        self.gun = Gun(MAX_BULLETS)

    def get_health(self):
        return self.health

    def get_gun(self):
        return self.gun

    def take_damage(self, damage):
        self.health -= damage

    def is_alive(self):
        return self.health > 0

    def has_bullets(self):
        return self.gun.get_num_bullets() > 0

def main():
    random.seed()

    player = Player()
    enemies = MAX_ENEMIES
    game_over = False

    while player.is_alive() and enemies > 0 and not game_over:
        print(f"Bullets: {player.get_gun().get_num_bullets()}")
        print(f"Enemies: {enemies}")
        print(f"Health: {player.get_health()}")

        command = input("Enter a command (shoot, reload, exit): ")

        if command == "shoot":
            if player.has_bullets():
                player.get_gun().shoot()

                if random.randint(0, 1) == 0:
                    enemies -= 1
                    print("You hit an enemy!")
                else:
                    print("You missed!")
            else:
                print("You don't have any bullets left!")
        elif command == "reload":
            if not player.has_bullets():
                player.get_gun().reload()
            else:
                print("Your gun is already full!")
        elif command == "exit":
            print("Thanks for playing, Made with chatGPT on 12/23/2022")
            game_over = True
            break
        else:
            print("Invalid command")

        if enemies > 0:
            damage = random.randint(10, 19)
            print(f"An enemy attack you for {damage} damage!")
            player.take_damage(damage)

    if not player.is_alive():
        print("You have been killed by the enemies!")
    elif not game_over:
        print("You have defeated all of the enemies!")

if __name__ == "__main__":
    main()
