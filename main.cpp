
#include "Animated.hpp"

#define H_FRAME 32
#define L_FRAME 32


int main()
{

    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Zelda");


    // On charge l'image qui contient nos animations
    sf::Image CharacterAnim;
    CharacterAnim.LoadFromFile("Link.png");
    CharacterAnim.CreateMaskFromColor(sf::Color(16,37,62));

    // On crée 4 animations (haut, bas, gauche, droite)
    Anim GoUp, GoRight, GoDown, GoLeft;

    // On définit nos animations frame par frame, en fournissant l'image et le SubRect
    GoDown.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(0, 0, 32, 32)));
    GoDown.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(32, 0, 64, 32)));
    GoDown.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(64, 0, 96, 32)));
    GoDown.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(96, 0, 128, 32)));

    GoLeft.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(0, 32, 32, 64)));
    GoLeft.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(32, 32, 64, 64)));
    GoLeft.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(64, 32, 96, 64)));
    GoLeft.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(96, 32, 128, 64)));

    GoRight.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(0, 128, 45, 192)));
    GoRight.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(45, 128, 90, 192)));
    GoRight.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(90, 128, 135, 192)));
    GoRight.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(135, 128, 190, 192)));

    GoUp.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(0, 192, 45, 256)));
    GoUp.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(45, 192, 90, 256)));
    GoUp.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(90, 192, 135, 256)));
    GoUp.PushFrame(Frame(&CharacterAnim, sf::Rect<int>(135, 192, 190, 256)));

    // On crée un sprite animé avec par défaut l'animation 'GoUp', en pause, mode Loop On, Et 0.1 seconde entre chaque frame
    Animated MyCharacter(&GoUp, false, true, 0.1f);
    MyCharacter.SetCenter(20, 32);
    MyCharacter.SetPosition(400, 300);

    // La boucle habituelle
    sf::Event Event;
    bool isRunning = true;
    while (isRunning)
    {
        while (Window.GetEvent(Event))
        {
            switch(Event.Type)
            {
                case sf::Event::Closed:
                isRunning = false;
                break;

                case sf::Event::KeyReleased:
                switch(Event.Key.Code)
                {
                    case sf::Key::Escape:
                    isRunning = false;
                    break;

                    default :
                    break;
                }
                default :
                break;
            }
        }

        Window.Clear();


        // On teste les déplacements

        // Gauche :
        if (Window.GetInput().IsKeyDown(sf::Key::Up))
        {

            // On applique l'anim si besoin est
            if (MyCharacter.GetAnim() != &GoUp)
                MyCharacter.SetAnim(&GoUp);

            // On déplace le sprite
            MyCharacter.Move(0, -100*Window.GetFrameTime());
            if(MyCharacter.IsPaused())
                MyCharacter.Play();
        }

        else if (Window.GetInput().IsKeyDown(sf::Key::Down))
        {
            if (MyCharacter.GetAnim() != &GoDown)
                MyCharacter.SetAnim(&GoDown);
            MyCharacter.Move(0, 100*Window.GetFrameTime());
            if(MyCharacter.IsPaused())
                MyCharacter.Play();
        }

        else if (Window.GetInput().IsKeyDown(sf::Key::Left))
        {
            if (MyCharacter.GetAnim() != &GoLeft)
                MyCharacter.SetAnim(&GoLeft);
            MyCharacter.Move(-100*Window.GetFrameTime(), 0);
            if(MyCharacter.IsPaused())
                MyCharacter.Play();
        }

        else if (Window.GetInput().IsKeyDown(sf::Key::Right))
        {
            if (MyCharacter.GetAnim() != &GoRight)
                MyCharacter.SetAnim(&GoRight);

            MyCharacter.Move(100*Window.GetFrameTime(), 0);
            if(MyCharacter.IsPaused())
                MyCharacter.Play();
        }
        else
        {
            // Si le perso arrette de se déplacer, on Stop l'animation
            if (!MyCharacter.IsStoped())
                MyCharacter.Stop();
        }

        // On appelle la fonction d'animation a chaque tours en donnant le temps écoulé
        MyCharacter.anim(Window.GetFrameTime());

        // Et on dessine
        Window.Draw(MyCharacter);

        Window.Display();
    }

    return EXIT_SUCCESS;
}
