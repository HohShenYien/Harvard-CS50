AI = Class{}
-- A simple AI for movement of 2nd playar (the one on the right)
-- First I will get the paddle and ball so that I can determine the position
-- of the ball compare to the paddle
function AI:init(paddle, ball)
    self.paddle = paddle
    self.ball = ball
end

function AI:checkUpDown(dt)
    -- This will determine if the ai successfully got the ball direction
    success = math.random(20) <= 17 and true or false
    -- If successful, then the paddle will move in the same direction of the ball
    -- If failed, then in opposite direction away from the ball
    if self.ball.y > self.paddle.y + self.paddle.height then
        if success then
            self.paddle.dy = PADDLE_SPEED 
        else
            self.paddle.dy = -PADDLE_SPEED 
        end
    elseif self.ball.y < self.paddle.y then
        if success then
            self.paddle.dy = -PADDLE_SPEED 
        else
            self.paddle.dy = PADDLE_SPEED 
        end
    -- If the ball is in the range of the paddle, then the paddle will stay
    -- if successful, if not it'll move randomly
    else
        if success then
            self.paddle.dy = 0
        else
            self.paddle.dy = math.random(2) == 1 and PADDLE_SPEED or -PADDLE_SPEED 
        end
    end
    -- Commit the movement predicted
    self.paddle.y = self.paddle.y + self.paddle.dy * dt 
end
