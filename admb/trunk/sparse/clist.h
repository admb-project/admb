#ifndef CLIST_H
#define CLIST_H
class clist
{
public :
  int length(const int & max = 1000);
protected :
  clist * next;
  clist()
  {
    next = this;
  }
  clist(const clist & pt);
  clist * prev(void);
public:
  ~clist();
};
#endif
