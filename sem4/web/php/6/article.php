<h1 class="mb-4 mb-xl-5">Fenomen ciudat: lui Ciucă i-a crescut IQ-ul cu 5 puncte după ce a stat lângă Nicuşor la meci</h1>

<p>Oamenilor de ştiinţă care îl studiază pe şeful Senatului nu le-a venit să creadă! După ce a stat aşezat lângă Nicuşor Dan pe durata meciului de retragere al generaţiei ’94, lui Ciucă i-ar fi crescut IQ-ul cu 3, 4 sau chiar 5 puncte.</p>


<p>Cel mai probabil, fenomenul se datorează aşa-numitei „radiaţii tocilăreşti” emanate de primarul Capitalei şi e total inofensiv şi reversibil, spun oamenii de ştiinţă, IQ-ul lui Ciucă urmând să revină la cota normală în decurs de câteva zile.</p>



<p>„Nu cunoaştem exact coeficientul de inteligenţă al dlui Ciucă, acesta fiind declarat secret de stat, ca în cazul tuturor înalţilor demnitari. Dar în dimineaţa de după meci, mai mulţi martori de încredere l-au văzut legându-se singur la şireturi, deci s-ar putea să avem prima dovadă empirică a acestei radiaţii tocilăreşti despre care se vorbeşte în ultimii ani”, a declarat Aristofan Creangă, cercetător la Institutul pentru Inteligenţă „Claudiu Răducanu” din Pantelimon.</p>



<p>„Eu sunt încă sceptic faţă de toate ipotezele astea cu radiaţii şi vibraţii. Poate totuşi au băut din aceeaşi sticlă sau au împărţit un hot dog”, îşi dă cu părerea Marinel Niţu, neuropsihiatru la Dispensarul Brăneşti.</p>
</div>


<?php
require_once "../config.php";
$conn = new PDO($db_path);
$result = $conn->prepare("SELECT * FROM comments WHERE state=1");
$result->execute();



echo "<h2>Comments:</h1>";

echo "<form action='add.php' method='POST'>
<input name='user'></input></br>
<textarea name='comment'></textarea>
<input type='submit' value='Send comment'></input>
</form>
";

while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
    $user = $row['user'];
    $comment = $row['comment'];
    echo "User: $user<br>";
    echo "Comment: $comment";
    echo "<br><br>";
}

?>
<a href='index.php'>Back</a>