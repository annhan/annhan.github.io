---
layout: default
title: 
---

**1.0 : Decorator  **

```
# function decorator that calls the function twice
def repeat_decorator(fn):
    def decorated_fn():
        fn()
        fn()
    # returns a function
    return decorated_fn

# using the decorator on hello_world function
@repeat_decorator
def hello_world():
    print ("Hello world!")

# call the function
hello_world()
```

**2.0 : Decorator với parameter **

```
def repeat_decorator(num_repeats = 2):
    # repeat_decorator should return a function that's a decorator
    def inner_decorator(fn):
        def decorated_fn():
            for i in range(num_repeats):
                fn()
        # return the new function
        return decorated_fn
    # return the decorator that actually takes the function in as the input
    return inner_decorator

# use the decorator with num_repeats argument set as 5 to repeat the function call 5 times
@repeat_decorator(5)
def hello_world():
    print("Hello world!")

# call the function
hello_world()
```