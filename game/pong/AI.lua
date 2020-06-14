AI = Class{}
-- A simple AI for movement of 2nd playar (the one on the right)
function AI:init(paddle, ball)
    self.paddle = paddle
    self.ball = ball
end

function AI:checkUpDown(dt)
    success = math.random(20) <= 17 and true or false
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
    else
        if success then
            self.paddle.dy = 0
        else
            self.paddle.dy = math.random(2) == 1 and PADDLE_SPEED or -PADDLE_SPEED 
        end
    end
    self.paddle.y = self.paddle.y + self.paddle.dy * dt 
end