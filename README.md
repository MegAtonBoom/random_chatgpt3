# random_chatgpt3

nothing much more to say about this repo, just testing programming stupid stuff with chat gpt3 

-snake.c: basic snake game, needed some changes from the original code to make some improvements,
    but it was actually very buggy in the first place: 
    1)The snake and food position were set correctly at the beginning but not used to print them (like wtf) making them spawn at the beginning of the first 2 rows, 
    not even moving
    2)After that, the prints of the snake were never cleared, so your snake would have grown indefinitely on the screen (but only a visual bug on the screen since the       metadata of the snake was correctly set, so you could have a graphic compenetration without a game over)
    3)I think it's an illegal move to go from a snake directed upwards to downwards in a refresh, resulting in the snake compenetrating itself if the lenght of the snake     is >1, so i changed his direction only if the move is ok
    
    ugly code but functional, surprised by the first two bugs wich were pretty huge
