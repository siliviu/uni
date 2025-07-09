import { Scene } from 'phaser';

const speed = 50;
const player_scale = 0.3;
const enemyMinScale = 0.2;
const enemyMaxScale = 0.5;
const baseEnemyHp = 100;
const damage = 10;

export class Game extends Scene {
    constructor() {
        super('Game');
        this.player1Score = 0;
        this.player2Score = 0;
        this.suspendedCollissions = [];
    }

    preload() {
        this.load.image('background_game', 'assets/game.webp');
        this.load.image('player1', 'assets/steve.png');
        this.load.image('player2', 'assets/alex.png');

        const enemies = [
            { name: 'slime', file: 'slime.png' },
            { name: 'magma', file: 'magma.png' },
        ];

        enemies.forEach(enemy => {
            this.load.image(enemy.name, `assets/${enemy.file}`);
        });

        this.enemies = enemies.map(enemy => enemy.name);

        for (let i = 1; i <= 10; i++) {
            this.load.image(`skash_${i.toString().padStart(5, '0')}`, `assets/skash_${i.toString().padStart(5, '0')}.png`);
        }
    }

    create() {
        this.add.image(960, 540, 'background_game').setScale(2, 2);


        this.player1 = this.physics.add.sprite(975, 525, 'player1')
            .setScale(player_scale)
            .setDepth(20)
            .setCollideWorldBounds(true)
            .setBounce(0.2);
        this.player2 = this.physics.add.sprite(825, 675, 'player2')
            .setScale(player_scale)
            .setDepth(20)
            .setCollideWorldBounds(true)
            .setBounce(0.2);

        this.initializeInputs();

        this.enemiesGroup = this.add.group({
            maxSize: 5
        });

        this.setupEnemySpawner();

        this.physics.add.collider(this.player1, this.enemiesGroup, this.handlePlayerEnemyCollision, null, this);
        this.physics.add.collider(this.player2, this.enemiesGroup, this.handlePlayerEnemyCollision, null, this);

        this.player1ScoreText = this.add.text(16, 16, 'Steve\'s score: 0', { fontSize: '32px', fill: '#FFF', fontWeight: 'bold' });
        this.player2ScoreText = this.add.text(1600, 16, 'Alex\'s score: 0', { fontSize: '32px', fill: '#FFF', fontWeight: 'bold' });

        this.anims.create({
            key: 'skash',
            frames: [
                { key: 'skash_00001' },
                { key: 'skash_00002' },
                { key: 'skash_00003' },
                { key: 'skash_00004' },
                { key: 'skash_00005' },
                { key: 'skash_00006' },
                { key: 'skash_00007' },
                { key: 'skash_00008' },
                { key: 'skash_00009' },
                { key: 'skash_00010' }
            ],
            frameRate: 5,
            repeat: 0
        });

        this.time.addEvent({
            delay: 3000,
            callback: this.spawnAnimatedObject,
            callbackScope: this,
            loop: true
        });
    }

    spawnAnimatedObject() {
        let overlap, x, y;
        do {
            overlap = false;
            x = Phaser.Math.Between(100, 1800);
            y = Phaser.Math.Between(100, 900);
            const tempSprite = this.add.sprite(x, y, 'skash_00001');

            [this.player1, this.player2].forEach(player => {
                if (Phaser.Geom.Intersects.RectangleToRectangle(tempSprite.getBounds(), player.getBounds())) {
                    overlap = true;
                }
            });

            this.enemiesGroup.getChildren().forEach(enemy => {
                if (Phaser.Geom.Intersects.RectangleToRectangle(tempSprite.getBounds(), enemy.getBounds())) {
                    overlap = true;
                }
            });

            if (overlap) {
                tempSprite.destroy();
            }
        } while (overlap);

        const animatedSprite = this.physics.add.sprite(x, y, 'skash_00001').play('skash');
        this.time.delayedCall(2000, () => animatedSprite.destroy());
    }


    initializeInputs() {
        this.cursors = this.input.keyboard.createCursorKeys();

        this.wasd = {
            up: this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.W),
            down: this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.S),
            left: this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.A),
            right: this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.D)
        };
    }

    setupEnemySpawner() {
        this.time.addEvent({
            delay: Phaser.Math.Between(750, 2500),
            callback: this.spawnEnemy,
            callbackScope: this,
            loop: true
        });
    }

    spawnEnemy() {
        if (this.enemiesGroup.countActive(true) < this.enemiesGroup.maxSize) {
            let overlap;
            let attempts = 0;
            let enemy;
            do {
                overlap = false;
                const x = Phaser.Math.Between(100, 1800);
                const y = Phaser.Math.Between(100, 950);
                const scale = Phaser.Math.FloatBetween(enemyMinScale, enemyMaxScale);
                const roundedScale = Math.round(scale * 10) / 10;
                const enemyName = this.enemies[Math.floor(Math.random() * this.enemies.length)];

                enemy = this.physics.add.sprite(x, y, enemyName).setScale(roundedScale).setImmovable(true);
                enemy.hp = Math.floor(roundedScale * baseEnemyHp);
                const radius = enemy.body.halfWidth;
                enemy.body.setCircle(radius);

                const enemyBounds = enemy.getBounds();

                this.enemiesGroup.getChildren().forEach(existingEnemy => {
                    if (Phaser.Geom.Intersects.RectangleToRectangle(enemyBounds, existingEnemy.getBounds())) {
                        overlap = true;
                    }
                });

                [this.player1, this.player2].forEach(player => {
                    if (Phaser.Geom.Intersects.RectangleToRectangle(enemyBounds, player.getBounds())) {
                        overlap = true;
                    }
                });

                if (overlap) {
                    enemy.destroy();
                } else {
                    enemy.hpBar = this.add.graphics();
                    enemy.hpText = this.add.text(x, y - 40, `HP: ${enemy.hp}`, { fontSize: '20px', fill: '#ff0000', fontWeight: 'bold' }).setOrigin(0.5);
                    this.enemiesGroup.add(enemy);
                }

                attempts++;
                if (attempts > 10) {
                    return;
                }
            } while (overlap);

            this.enemiesGroup.add(enemy);
        }
    }

    updateHealthBar(enemy) {
        enemy.hpBar.clear();
        enemy.hpBar.fillStyle(0xff0000, 1);
        enemy.hpBar.fillRect(enemy.x - enemy.body.width / 2, enemy.y, enemy.body.width * (enemy.hp / (enemy.scale * baseEnemyHp)), 5);
    }

    handlePlayerEnemyCollision(player, enemy) {
        const collisionKey = `${player.name}-${enemy.name}`;

        if (this.suspendedCollissions.includes(collisionKey) || player.slowText) {
            return;
        }
        this.suspendedCollissions.push(collisionKey);

        let multiplier = 1;

        switch (enemy.texture.key) {
            case 'slime':
                this.animateBounce(player, enemy);
                break;
            case 'magma':
                this.applySlowEffect(player, 0.7, 1500);
                this.showSlowEffect(player);
                multiplier = 1 + Math.random();
                break;
        }
        console.log(`Collision between ${player.texture.key} and ${enemy.texture.key}. ${multiplier}`);

        enemy.hp -= Math.floor(multiplier * (damage - Math.floor(enemy.scale * 4) + Math.floor(Math.random() * 3)));
        if (enemy.hp <= 0) {
            if (player === this.player1) {
                this.player1Score += enemy.scale * 10;
                this.player1ScoreText.setText('Steve\'s score: ' + this.player1Score);
            } else if (player === this.player2) {
                this.player2Score += enemy.scale * 10;
                this.player2ScoreText.setText('Alex\'s score: ' + this.player2Score);
            }
            enemy.hpBar.destroy();
            enemy.hpText.destroy();
            enemy.destroy();

            if (this.player1Score >= 30 || this.player2Score >= 30) {
                this.scene.start('GameOver');
            }
        } else {
            enemy.hpText.setText(`HP: ${enemy.hp}`);
            this.updateHealthBar(enemy);
        }

        this.time.delayedCall(150, () => {
            this.suspendedCollissions = this.suspendedCollissions.filter(item => item !== collisionKey);
        }, [], this);
    }

    applySlowEffect(player, slowFactor, duration) {
        player.setData('speed', speed * slowFactor);
        this.time.delayedCall(duration, () => {
            player.setData('speed', speed);
        }, [], this);
    }

    showSlowEffect(player) {
        const slowText = this.add.text(player.x, player.y - 70, 'In flames!', { fontSize: '48px', fill: '#950606', fontStyle: 'bold', zIndex: 3000 }).setOrigin(0.5);
        slowText.setAlpha(0.7);
        player.slowText = slowText;

        this.tweens.add({
            targets: slowText,
            alpha: 0,
            duration: 2000,
            ease: 'Linear',
            onComplete: () => {
                slowText.destroy();
                player.slowText = null;
            }
        });
    }


    animateBounce(player, enemy) {
        const dx = player.x - enemy.x;
        const dy = player.y - enemy.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        const bounceDistance = 175;

        const bounceBackX = player.x + (dx / dist) * bounceDistance;
        const bounceBackY = player.y + (dy / dist) * bounceDistance;

        this.tweens.add({
            targets: player,
            x: bounceBackX,
            y: bounceBackY,
            duration: 125,
            ease: 'Sine.easeInOut',
            repeat: 0,
            onStart: () => {
            },
            onComplete: () => {
            }
        });
    }

    update(time, delta) {
        this.calculatePlayerMovement(this.cursors, this.player1, delta);
        this.calculatePlayerMovement(this.wasd, this.player2, delta)
        this.updatePlayerText(this.player1);
        this.updatePlayerText(this.player2);
    }

    updatePlayerText(player) {
        if (player.slowText) {
            player.slowText.setPosition(player.x, player.y - 70);
        }
    }

    calculatePlayerMovement(controls, player, delta) {
        const currentSpeed = player.getData('speed') || speed;
        player.setVelocity(0);

        let velocityX = 0;
        let velocityY = 0;

        if (controls.left.isDown) {
            velocityX -= currentSpeed;
            player.scaleX = -Math.abs(player.scaleX);
            player.body.offset.x = player.width;
        }
        if (controls.right.isDown) {
            velocityX += currentSpeed;
            player.scaleX = Math.abs(player.scaleX);
            player.body.offset.x = 0;
        }
        if (controls.up.isDown) {
            velocityY -= currentSpeed;
        }
        if (controls.down.isDown) {
            velocityY += currentSpeed;
        }

        if (velocityX !== 0 && velocityY !== 0) {
            const diagSpeed = Math.sqrt(velocityX * velocityX + velocityY * velocityY);
            player.setVelocityX((velocityX / diagSpeed) * currentSpeed * delta);
            player.setVelocityY((velocityY / diagSpeed) * currentSpeed * delta);
        } else {
            player.setVelocityX(velocityX * delta);
            player.setVelocityY(velocityY * delta);
        }
    }
}
