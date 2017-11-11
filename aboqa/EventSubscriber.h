//
//  EventSubscriber.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#ifndef EventSubscriber_h
#define EventSubscriber_h

template <typename... Args>
class EventPublisher;

template <typename... Args>
class EventSubscriber
{
public:
    virtual ~EventSubscriber ()
    { }

protected:
    friend class EventPublisher<Args...>;
    
    virtual void notify (Args... args) = 0;
};

#endif /* EventSubscriber_h */
