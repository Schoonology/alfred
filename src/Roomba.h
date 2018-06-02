class Roomba {
public:
  static void begin();
  static void send(unsigned char byte);
  static void wake();
  static void sleep();
  static void _reset();
  static void start();
  static void stop();
  static void clean();
  static void dock();
};
