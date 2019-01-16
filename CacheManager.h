#ifndef SERVER_CACHEMANAGER_H
#define SERVER_CACHEMANAGER_H


template<typename Problem, typename Solution>
class CacheManager {

public:

    virtual bool isSavedInCache(Problem p) = 0;

    virtual Solution getFromCache(Problem problem) = 0;

    virtual void saveSLNForProblem(Problem p, Solution s) = 0;

     virtual ~CacheManager(){};
};


#endif //SERVER_CACHEMANAGER_H
