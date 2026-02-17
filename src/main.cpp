#include "vane/world.hpp"


int main(int argc, char **argv)
{
    vane::World world;

    while (true)
    {
        world.update();
    }

    return 0;
}