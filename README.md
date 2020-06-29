<font face = "Consolas">

# WangGH_AirBattleGame

**项目名称：           游戏——飞机大战v2.0**

**项目简介：**

  > 一个控制台小游戏，之前根据所学实现了飞机大战（没有上传），功能较少，内容较简单，仅仅作为娱乐
  > 
  > 后来决定在1.0的基础上进行继续创作，同时也是对自己所学知识的巩固，对能力的一种锻炼
  > 
**游戏规则：**
  >
  > 玩家操作一架飞机进行移动和攻击，击毁敌机以得分。
  >   <br/><br/>
  > *w a s d* 控制移动
  >
  > *j*  普通攻击，无消耗，发出两排子弹，每排3个
  >
  > *k* 为技能1，消耗能量值50，技能效果为扫射，发出多排子弹，每排7个
  >
  > *l* 为技能2，消耗能量值20，缓慢恢复生命值10点（生命值上限为100）
  >
  > *Esc* 为暂停，再按任意键继续 
  >   <br/><br/>
  > 敌机不会攻击，但玩家要避免与敌机相撞，同时防止敌机移动到界面底部。 
  >
  > 游戏积分不设置上限，没有获胜条件，当血量为0时游戏结束。
  > 
  > 每次击中敌机得分+1，能量+2，生命不会通过击毁敌机回复。
  > 
  > 为了降低游戏难度，飞机与敌机相撞时，若生命大于50，则会保留一点生命，否则生命减为0。
  > 
  > 每次敌机到达界面底部时，生命-10；若能量回复因子到达底部，能量+2。
  > 
  > 击中或碰到能量回复因子时，能量+30，得分+1（能量上限为100）。

**项目进度：**

  > 版本v2.0已基本完成，目前尚未发现严重bug。
  > 
  > 版本v3.0正在完善中，由于会大量更新新内容，时间会比较久，故更新时间和内容待定。
  > 
  > 关于新版本，目前想法如下：(仅仅只是想法，可能不会体现新版本中)
  > 
  > 1）计划加入存档功能，并设置游戏虚拟货币，以每次游戏结束时的得分为标准发放。
  > 
  >    货币可在商店内购买其他战机，每架战机有不同技能，可供玩家选择。
  >    
  > 2）计划对游戏设置不同难度，从敌机数量和敌机速度体现。
  > 
  >    每次开局可供玩家选择初始难度，并随着每局游戏进行难度逐渐递增。
  >    
  >    初始难度选择不同，奖励发放的标准也会不同。
  > 
  > 同时有可能在3.0中实现图形化和界面化，不再局限于控制台。
  >                             
  >   <br/>     <br/>            
  > 本人能力有限，可能项目有较大弊端，欢迎各位提出自己的看法
  >   <br/>  <br/>                                               
  > 本代码仅用于交流学习，未经允许禁止用作其他商业行为，禁止用来交课堂/期末作业
  > 
  > 如果想引用部分代码进行创作并上传网络, 请注明原作者
  
