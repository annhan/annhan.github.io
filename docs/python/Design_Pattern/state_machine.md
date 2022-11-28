---
layout: default
title: 
---

```python

class State(object):

    def __init__(self):
        pass

    @property
    def name(self):
        return ''

    def enter(self, machine):
        pass

    def exit(self, machine):
        pass

    def update(self, machine):
        if switch.fell:
            machine.paused_state = machine.state.name
            machine.pause()
            return False
        return True

class StateMachine(object):

    def __init__(self):
        self.state = None
        self.states = {}
        self.firework_color = 0
        self.firework_step_time = 0
        self.burst_count = 0
        self.shower_count = 0
        self.firework_stop_time = 0
        self.paused_state = None
        self.pixels = []
        self.pixel_index = 0

    def add_state(self, state):
        self.states[state.name] = state

    def go_to_state(self, state_name):
        if self.state:
            log('Exiting %s' % (self.state.name))
            self.state.exit(self)
        self.state = self.states[state_name]
        log('Entering %s' % (self.state.name))
        self.state.enter(self)

    def update(self):
        if self.state:
            log('Updating %s' % (self.state.name))
            self.state.update(self)

    # When pausing, don't exit the state
    def pause(self):
        self.state = self.states['paused']
        log('Pausing')
        self.state.enter(self)

    # When resuming, don't re-enter the state
    def resume_state(self, state_name):
        if self.state:
            log('Exiting %s' % (self.state.name))
            self.state.exit(self)
        self.state = self.states[state_name]
        log('Resuming %s' % (self.state.name))

    def reset_fireworks(self):
        """As indicated, reset the fireworks system's variables."""
        self.firework_color = random_color()
        self.burst_count = 0
        self.shower_count = 0
        self.firework_step_time = time.monotonic() + 0.05
        strip.fill(0)
        strip.show()

class PausedState(State):

    def __init__(self):
        self.switch_pressed_at = 0
        self.paused_servo = 0

    @property
    def name(self):
        return 'paused'

    def enter(self, machine):
        State.enter(self, machine)
        self.switch_pressed_at = time.monotonic()
        if audio.playing:
            audio.pause()
        self.paused_servo = servo.throttle
        servo.throttle = 0.0

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if switch.fell:
            if audio.paused:
                audio.resume()
            servo.throttle = self.paused_servo
            self.paused_servo = 0.0
            machine.resume_state(machine.paused_state)
        elif not switch.value:
            if time.monotonic() - self.switch_pressed_at > 1.0:
                machine.go_to_state('waiting')
				
class WaitingState(State):
  
    @property
    def name(self):
        return 'waiting'

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def almost_NY(self):
        t = rtc.datetime
        return (t.tm_mday == 31 and
                t.tm_mon == 12 and
                t.tm_hour == 23 and
                t.tm_min == 59 and
                t.tm_sec == 50)

    def update(self, machine):
        if switch.fell or self.almost_NY():
            machine.go_to_state('dropping')
			
class DroppingState(State):

    def __init__(self):
        self.rainbow = None
        self.rainbow_time = 0
        self.drop_finish_time = 0

    @property
    def name(self):
        return 'dropping'

    def enter(self, machine):
        State.enter(self, machine)
        now = time.monotonic()
        start_playing('./countdown.wav')
        servo.throttle = DROP_THROTTLE
        self.rainbow = rainbow_lamp(range(0, 256, 2))
        self.rainbow_time = now + 0.1
        self.drop_finish_time = now + DROP_DURATION

    def exit(self, machine):
        State.exit(self, machine)
        now = time.monotonic()
        servo.throttle = 0.0
        stop_playing()
        machine.reset_fireworks()
        machine.firework_stop_time = now + FIREWORKS_DURATION

    def update(self, machine):
        if State.update(self, machine):
            now = time.monotonic()
            if now >= self.drop_finish_time:
                machine.go_to_state('idle')
            if now >= self.rainbow_time:
                next(self.rainbow)
                self.rainbow_time = now + 0.1
				
class IdleState(State):

    @property
    def name(self):
        return 'idle'

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        State.update(self, machine)
```		
		
Và main loop

```python
machine = StateMachine()
machine.add_state(PausedState())
machine.add_state(WaitingState())
machine.add_state(DroppingState())
machine.add_state(IdleState())

machine.go_to_state('waiting')

while True:
    switch.update()
    machine.update()
```