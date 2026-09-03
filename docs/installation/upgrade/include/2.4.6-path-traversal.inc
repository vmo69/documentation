 * Authentication now fails for any username whose `/` or `@` delimited
   component consists only of dots, e.g. `..`, `..@example.com` or
   `user@..`. Such a component escapes its parent directory when the username
   is used in a path, e.g. in [[setting,mail_path]], [[setting,mail_home]] or
   a dict key. The check is independent of [[setting,auth_username_chars]]
   and also applies to usernames returned by a passdb or userdb. Ordinary
   dotted usernames like `first.last@example.com` are unaffected. Accounts
   with such a username can no longer log in or be looked up; none should
   exist, since they were never valid RFC 5322 addresses.
 * The same rule applies to the owner part of a shared mailbox name, e.g.
   `shared/../INBOX`. Such a mailbox is reported as nonexistent.
 * After `%variable` expansion, [[setting,mail_home]], [[setting,mail_path]],
   [[setting,mail_index_path]], [[setting,mail_index_private_path]],
   [[setting,mail_cache_path]], [[setting,mail_control_path]] and
   [[setting,mail_alt_path]] are normalized (`.` and `..` components are
   resolved) and must still begin with the literal part of the setting
   preceding its first variable, e.g. `/var/vmail/%{user | domain}/%{user |
   username}` must stay under `/var/vmail/`. Otherwise the user's settings
   are invalid and the login fails. Values returned by the userdb or given
   with `-o` are not templates and are only normalized. Symbolic links are
   not resolved. This matches what [[setting,passwd_file_path]] has done
   since v2.3.
