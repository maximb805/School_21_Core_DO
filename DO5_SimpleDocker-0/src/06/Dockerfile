FROM ubuntu/nginx
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./entrypoint.sh /
RUN  apt-get -y update; \
     apt-get -y upgrade; \
     apt-get -y install gcc libfcgi-dev spawn-fcgi; \
     chmod u-s usr/bin/chfn; \
     chmod u-s usr/bin/passwd; \
     chmod u-s usr/bin/gpasswd; \
     chmod u-s usr/bin/newgrp; \
     chmod u-s bin/mount; \
     chmod g-s usr/bin/wall; \
     chmod u-s usr/bin/chsh; \
     chmod u-s bin/su; \
     chmod g-s usr/bin/chage; \
     chmod g-s usr/bin/expiry; \
     chmod g-s sbin/unix_chkpwd; \
     chmod u-s bin/umount; \
     chmod g-s usr/sbin/pam_extrausers_chkpwd; \
     chown -R nginx:nginx /var/log/nginx; \
     chown -R nginx:nginx /var/lib/nginx/; \
     touch /var/run/nginx.pid; \
     chown -R nginx:nginx /var/run/nginx.pid; \
     chown -R nginx:nginx /home; \
     chown -R nginx:nginx /etc/nginx; \
     rm -rf /var/lib/apt/lists
USER nginx
HEALTHCHECK --interval=5m --timeout=3s CMD curl -f http://localhost/ || exit 1
CMD  ["/entrypoint.sh"]
