#ifndef CONTACT_LISTENER_H_
#define CONTACT_LISTENER_H_

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener {
   public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif