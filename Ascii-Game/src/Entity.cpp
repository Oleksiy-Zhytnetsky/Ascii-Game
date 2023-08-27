#include "headers/Entity.h"

void Entity::attack(Entity &other) {
    if (other.get_healthpoints() <= get_damage()) other.set_healthpoints(0);
    else other.set_healthpoints(other.get_healthpoints() - get_damage());
}
