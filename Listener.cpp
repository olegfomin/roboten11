
#include "Listener.h";

Listener::Listener() {
  
}

// short description must not be over 16 chars
bool Listener::onEvent(unsigned int code, String description, String shortDescription) {
  return false;
}
