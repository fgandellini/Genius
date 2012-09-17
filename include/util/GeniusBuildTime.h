#ifndef D_GeniusBuildTime_H
#define D_GeniusBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  GeniusBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class GeniusBuildTime
  {
  public:
    explicit GeniusBuildTime();
    virtual ~GeniusBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    GeniusBuildTime(const GeniusBuildTime&);
    GeniusBuildTime& operator=(const GeniusBuildTime&);

  };

#endif  // D_GeniusBuildTime_H
