#include "app.h"

int main(void)
{
  App *app = new_App(3000, "127.0.0.1");
  app->run(app);
  delete_App(app);
  return 0;
}
