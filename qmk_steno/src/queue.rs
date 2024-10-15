use steno_engine::{dictionary::packed, keycode};

pub struct Queue {
    buf: [Option<packed::Event>; 128],
    start: usize,
    end: usize,
}

impl Queue {
    pub fn new() -> Self {
        Self {
            buf: [None; 128],
            start: 0,
            end: 0,
        }
    }

    pub fn push(&mut self, event: keycode::Event) {
        let new_end = if self.end == self.buf.len() - 1 {
            0
        } else {
            self.end + 1
        };
        assert_ne!(new_end, self.start);
        self.buf[self.end] = Some(event.try_into().unwrap());
        self.end = new_end;
    }

    pub fn pop(&mut self) -> Option<keycode::Event> {
        if self.start == self.end {
            return None;
        }
        let new_start = if self.start == self.buf.len() - 1 {
            0
        } else {
            self.start + 1
        };
        let out = self.buf[self.start].take().map(|e| e.into());
        self.start = new_start;
        out
    }
}
