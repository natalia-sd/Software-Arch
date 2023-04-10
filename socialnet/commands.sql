use archdb; 
show tables;
CREATE TABLE IF NOT EXISTS `User` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(256) NOT NULL,
  `last_name` VARCHAR(256) NOT NULL,
  `login` VARCHAR(256) NOT NULL,
  `pswd` VARCHAR(256) NOT NULL,
  `email` VARCHAR(256) NULL,
  `birthday` VARCHAR(256) NULL,
  PRIMARY KEY (`id`));
  INSERT INTO User (first_name, last_name, login, pswd, email, birthday)
VALUES ('Alice', 'Dalley', 'alicedal', '123456', 'alicedalley12@gmail.com', '13.08.1976'),
       ('Ben', 'Cintey', 'bennycinty', 'qwerty', 'bencint@gmail.com', '22.04.2000'),
       ('Cara', 'Brown', 'carbee', 'password', 'carabrown99@gmail.com', '31.12.1999'),
       ('Daniel', 'Aberfort', 'aberdan', 'aber123', 'DanielAber@gmail.com', '01.05.1989');
CREATE TABLE IF NOT EXISTS `Message` (
  `message_id` INT NOT NULL AUTO_INCREMENT,
  `sender_id` INT NOT NULL,
  `receiver_id` INT NOT NULL,
  `text_message` VARCHAR(256) NULL,
  PRIMARY KEY (`message_id`));
INSERT INTO Message (sender_id, receiver_id, text_message)
VALUES (1, 2, 'Hi, mate! whats up?'),
       (2, 1, 'long time no see alice! nothing rn, just chillin'),
       (3, 4, 'Hey Dan, our meeting is at 2 PM EST this tuesday'),
       (4, 3, 'Great, copy that. Is Ellen supposed to be there too?');  
 CREATE TABLE IF NOT EXISTS `Wall` (
  `post_id` INT NOT NULL AUTO_INCREMENT,
  `user_id` INT NOT NULL,
  `post_title` VARCHAR(256) NOT NULL,
  `post_text` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`post_id`));   
INSERT INTO Wall (user_id, post_title, post_text)
VALUES (1, 'Turkey trip September 2022', 'This was awesome!'),
       (2, 'Updates on my 30 days challenge!', 'Day 15 going well...'),
       (3, 'Total Redisign', 'We have totally changed the whole concept of our future house, see below.'),
       (4, 'Jungle Fever Party 08/08/23', 'Here are the new pricelist and DJ lineup.');