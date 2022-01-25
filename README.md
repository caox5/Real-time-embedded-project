<h2>Principles and Methodology</h2><hr><br>
In this project, Developers tye to use camera to capture the bones guesture and analzying it. According to the study of fall characteristics, because of the falling is an instant action, developers are supposed to consider either human feature detection or action recognition. <br>
<ul>
  <li>1. Human feature detection: By using some methodology to extract the human from the background and then analzye the feature</li>
  <li>2. Action recognition: By analyzing the specific points to judge whether human is falling or not.  
</ul>


<hr>
<h2>Our Methodology</h2>
We deceide to use the second methodology, by selecting several points from the skeleton graph, for example, we could set the mid point on human chest, set the second mid point on pelvis, then calculating the space position and move speed to judge whether human is falling or not. In specificly, there are two necessary ways to make sure human is falling:
<ul>
  <li>1. because of we set the chest as the upper half of human body's mid point. we could conclude if the midpoint's falling acclaration is greather than a speciifc threshold(we use 1.5m/s here), then this human is falling.</li>
   <li>2. Once the first detection is passed, the second detection is check the mid points on lower half of human body, which is pelvis. Calculating the distance between pelvis and ground, if the distance is less than 5cm, and this posture is last for 5 seconds, combine with first option, we could conclude that human is fall. 
</ul><br>

After that we could call guardian or send the live video to him/her.
