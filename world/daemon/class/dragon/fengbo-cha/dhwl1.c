// dhwl.c
//write by yeahsi
//yeahsi@21cn.com

#include <ansi.h>

inherit SSERVER;


int perform(object me, object target)
{
    int how_long,times;
    string str;
    object weapon;
    
    if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ������������\n");
    
    
    if (!me->query_temp("dhwl"))
           return notify_fail("��û��������\n");
           
    if (me->query_temp("dhwl_target") != target)
           return notify_fail("���������˰ɡ�\n");              
           
    weapon=me->query_temp("weapon");
    how_long = me->query_temp("dhwl");
    times = random(how_long)+1;
    if (how_long > 6 && times < 6) times=5;
    if (how_long > 10) times=10;
    
    
    message_vision(HIC"$N��Хһ�������Ϊ֮��ɫ������"+weapon->name()+HIC"����һ����������ĺ����������������Ϯ��$n��
$nֻ����$N���������������Ժ��ɰٴ��������һ�˽�һ��������������Ҳ�е������ˡ�\n"NOR,me,target);

    me->delete_temp("no_move");
    me->add_temp("apply/damage",how_long*5);
    me->add_temp("apply/attack", how_long*5);  
    for (int i=0; i<=times; i++)
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    
    if (target->query("eff_kee")<0 || !living(target))  
                       {str=target->name()+"����"+me->name()+"�ġ�������������"+me->name()+"���������£���ʱ��Ѫ������";
	                CHANNEL_D->do_channel(me, "rumor",str);
	                me->delete_temp("last_channel_msg");}

    me->set_temp("apply/dodge",me->query_temp("before_dhwl_dodge"));
    me->delete_temp("dhwl");
    me->delete_temp("before_dhwl_dodge");
    me->add_temp("apply/damage",-how_long*5);
    me->add_temp("apply/attack", -how_long*5);
    me->set_temp("dhwl_end",time());
    me->delete_temp("dhwl_target");
    return 1;
	        
        
}
